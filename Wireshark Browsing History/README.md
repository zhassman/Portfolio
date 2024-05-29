## Wireshark Browsing History Project

### Overview
This project involves scripts designed to reconstruct the browsing history of a user nicknamed "ghost". It utilizes techniques in web scraping, network traffic analysis, and pathfinding based on network data to accurately model user behavior online.

### Scripts

- **`buildWebsiteGraph.py`**
  - **Purpose**: Creates a website graph from a starting URL using a breadth-first search (BFS) up to 22 layers deep, to trace the network of sites visited.
  - **Output**: JSON formatted data representing the website relationship graph.

- **`cleanUpSiteGraph.py`**
  - **Purpose**: Enhances the website graph with data about the network size of each site, providing a more detailed understanding of the user's interaction with each site.
  - **Output**: An updated JSON file including site sizes.

- **`parseGhost.py`**
  - **Purpose**: Analyzes network packet data specifically related to "ghost's" activity, to assess the size of the sites visited based on network traffic.
  - **Output**: JSON file detailing site size data derived from network traffic analysis.

- **`parseMine.py`**
  - **Purpose**: Computes the total acknowledgment bytes sent across all network flows for defined sites, offering insights into the data volume exchanged during "ghost's" browsing sessions.
  - **Output**: JSON file summarizing the total acknowledgment bytes per site.

- **`recreateBrowsingHistory.py`**
  - **Purpose**: Uses the computed site sizes and their network relationships to recreate "ghost's" probable sequence of visited sites, simulating the browsing path taken.
  - **Output**: A list depicting the most likely sequence of sites visited by "ghost".

- **`simplifyJSON.py`**
  - **Purpose**: Streamlines the network packet data to focus only on essential information, facilitating more efficient subsequent analyses.
  - **Output**: A simplified JSON file optimized for quicker processing and analysis.
