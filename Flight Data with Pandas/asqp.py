import numpy as np
import pandas as pd
import utils


def read_and_process_asc(filename):
    """
    Read in and process a ASC file from the ASQP data set

    Input:
        filename (string): name of the file

    Returns (Pandas DataFrame): a Pandas DataFrame with the ASQP data
    """
    type_dict = {"Date": str, 'Departure Scheduled CRS': str, 
    'Arrive Scheduled CRS': str, "Takeoff": str, "Landing": str, 
    'Arrive Actual Gate': str, 'Departure Actual Gate': str, 
    'Arrive Scheduled OAG': str, 'Departure Scheduled OAG': str,
    'Marketing Carrier Flight Number': str, 
    'Planned Operating Carrier Flight Number':str, 
    'Actual Operating Carrier Flight Number': str}

    try:
        df = pd.read_csv(filename, delimiter = "|", dtype = type_dict, 
                                                            low_memory=False)
    except FileNotFoundError:
        return None

    df["Date"] = pd.to_datetime(df["Date"])

    df["Year"] = df["Date"].dt.year
    df["Month"] = df["Date"].dt.month
    df["Day"] = df["Date"].dt.day

    df["Day of Week"].replace(utils.DAYS_OF_WEEK, inplace=True)

    to_pad_and_convert = ["Departure Scheduled CRS", "Arrive Scheduled CRS", 
    "Arrive Actual Gate", "Departure Actual Gate", "Arrive Scheduled OAG", 
    "Departure Scheduled OAG", "Takeoff", "Landing"]

    for col in to_pad_and_convert:
        df[col] = df[col].str.pad(4, side="left", fillchar="0")
        df[col] = pd.to_datetime(df[col], format="%H%M", errors="coerce")

    lbls = ["Overnight", "Morning", "Afternoon", "Evening"]
    bns = [0, 5, 11, 17, 23]
    df["Period"] = pd.cut(x=df["Departure Scheduled CRS"].dt.hour, labels=lbls, 
                                                bins=bns, include_lowest=True)

    df["Operator"] = df["Actual Operating Carrier"].replace(utils.CARRIERS)

    maineline_carriers = ["American", "Delta", "Southwest", "United"]
    df["Mainline"] = df["Operator"].isin(maineline_carriers).replace(
                                        {True: "Mainline", False: "Regional"})

    df["Cancellation Code"].replace(utils.CANCELLATION_REASONS, inplace=True)
    df.rename(columns={"Cancellation Code": "Cancellation Reason"}, 
                                                                inplace=True)

    df["Cancelled?"] = df["Cancellation Reason"].notnull()

    df["Delayed?"] = df["Arrival Delay"] >= 15

    return df


def delay_and_cancel_fractions(df):
    """
    Given ASQP data, compute the fraction of delayed and cancelled flights

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (tuple of floats): fraction of flights that were delayed,
        fraction of flights that were cancelled
    """
    try:
        del_frac = df["Delayed?"].value_counts()[True] / df["Delayed?"].count()
    except KeyError:
        del_frac = 0
    try:
        can_frac = df["Cancelled?"].value_counts()[True] / df["Cancelled?"]\
                                                                        .count()
    except KeyError:
        can_frac = 0
    
    return (del_frac, can_frac)


def per_carrier_delays_cancels(df):
    """
    Given ASQP data, determine how many of each carrier's flights were
        delayed or cancelled

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (tuple of DataFrame): delays by carrier, cancellations per carrier
    """
    del_df = df[df["Delayed?"]]["Operator"].value_counts().to_frame()
    can_df = df[df["Cancelled?"]]["Operator"].value_counts().to_frame()

    return (del_df, can_df)


def average_delay(df):
    """
    Given ASQP data, determine the average flight delay

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (float): the average delay
    """
    nonearly = df["Arrival Delay"] >= 0
    return df[nonearly]["Arrival Delay"].mean()


def average_delay_by_period(df):
    """
    Given ASQP data, determine whether or not delays get worse throughout
        the day

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (DataFrame): the average delay per period of day
    """
    nonearly = df["Arrival Delay"] >= 0
    return df[nonearly].groupby("Period")["Arrival Delay"].mean().to_frame()


def underperforming_carriers(df):
    """
    Given ASQP data, determine which carriers have a worse than average delay

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (DafaFrame): underperforming carriers and their average delay
    """
    avg_delay = average_delay(df)
    nonearly = df["Arrival Delay"] >= 0
    mean_del_by_op = df[nonearly].groupby("Operator")["Arrival Delay"].mean()
    worse_than_mean = mean_del_by_op > avg_delay
    return mean_del_by_op[worse_than_mean].to_frame()


def read_and_process_npy(filename):
    """
    Read in and process time series ASQP data

    Input:
        filename (string): name of the NPY file

    Returns (NumPy array): a time series NumPy array
    """
    delays = np.load(filename)

    time_series = np.zeros(utils.TIME_SERIES_DATA_LEN)
    is_short = delays < 60
    delays[is_short] = 0
    time_series = np.count_nonzero(delays, axis=1)

    return time_series


def remove_irregularities(ts, width):
    """
    Apply a smoothing technique to remove irregularities from the
        times series ASQP data

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe

    Returns (NumPy array): smoothed time series data
    """
    smooth_ts = []

    for index in range(utils.TIME_SERIES_DATA_LEN):
        smooth_ts.append(np.mean(ts[max(0, index - width):min(index + width, 
                                            utils.TIME_SERIES_DATA_LEN) + 1]))

    return np.array(smooth_ts)


def remove_trend(ts, width):
    """
    Remove overall trend from time series ASQP data

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe

    Returns (NumPy array): detrended time series data
    """
    smooth_ts = remove_irregularities(ts, width)
    m, _ = utils.perform_least_squares(smooth_ts)
    return ts - (m * np.arange(utils.TIME_SERIES_DATA_LEN))


def is_seasonal(ts, width):
    """
    Bucket late flights, determine the bucket with the most
        late flights

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe
        list_of_indices (lit of list of ints): something here

    Returns (NumPy array, int): number of delays in each month,
        the index of the month with the most delays (January = 0, etc.)
    """
    trendless_ts = remove_trend(ts, width)
    year_array = trendless_ts.reshape(3,12)
    buckets = np.sum(year_array, axis=0)
    return (buckets, np.argmax(buckets))
