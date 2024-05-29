## Wireshark Browsing History

### Project Overview

This folder contains scripts for a computer security project aimed at reconstructing the browsing history of a user termed "ghost". The project involves:
- Generating a website graph from a known starting point (`buildWebsiteGraph.py`).
- Enhancing this graph with data about the network size of each site (`cleanUpSiteGraph.py`).
- Analyzing packet data to calculate network sizes (`parseGhost.py` and `parseMine.py`).
- Recreating the most probable browsing path based on these sizes (`recreateBrowsingHistory.py`).
- Simplifying packet data for efficient processing (`simplifyJSON.py`).

The project showcases advanced techniques in web scraping, network traffic analysis, data processing, and heuristic-based pathfinding to model user behavior on the internet accurately.

### File Descriptions

**1. `buildWebsiteGraph.py`:**
   - Builds a graph of websites by exploring links from a starting URL using a breadth-first search (BFS) algorithm up to 22 layers deep. Collects neighboring URLs, saves them, and stores the relationship data in JSON format.

**2. `cleanUpSiteGraph.py`:**
   - Reads a JSON file containing site relationships and another JSON file containing sizes of these sites. Updates the original graph with site sizes and outputs the enriched data to a new JSON file.

**3. `parseGhost.py`:**
   - Analyzes network packet data to calculate the total acknowledgment bytes sent across all flows for each site within a specified time frame. The results are used to assess the size of each site based on network traffic and are saved in JSON format.

**4. `parseMine.py`:**
   - Processes packet data to compute the total acknowledgment bytes for defined sites. Isolates packets per site and calculates totals, storing the results in a JSON file.

**5. `recreateBrowsingHistory.py`:**
   - Utilizes the computed site sizes and neighbor relationships to reconstruct the browsing history of a user named "ghost". Implements recursive pathfinding based on size comparisons between the actual site and recorded data, aiming to match browsing patterns as closely as possible.

**6. `simplifyJSON.py`:**
   - Processes detailed network packet data, extracting key information such as TCP flags and DNS queries. This simplification helps focus subsequent analyses on essential data, facilitating more efficient processing.
