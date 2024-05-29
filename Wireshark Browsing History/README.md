## Wireshark Browsing History Project

### Overview
This project involves scripts to reconstruct a user's browsing history, demonstrating techniques in web scraping, traffic analysis, and pathfinding based on network data.

### Scripts

- **`buildWebsiteGraph.py`**
  - **Purpose**: Creates a website graph from a URL using BFS up to 22 layers deep.
  - **Output**: JSON format relationship data.

- **`cleanUpSiteGraph.py`**
  - **Purpose**: Enhances a website graph with site size data.
  - **Output**: Updated JSON file with site sizes.

- **`parseGhost.py`**
  - **Purpose**: Analyzes network packet data to assess site sizes.
  - **Output**: JSON file with site size data based on traffic.

- **`parseMine.py`**
  - **Purpose**: Computes acknowledgment bytes from network packets for defined sites.
  - **Output**: JSON file with total acknowledgment bytes per site.

- **`recreateBrowsingHistory.py`**
  - **Purpose**: Recreates a user's browsing history using computed site sizes.
  - **Output**: Probable sequence of visited sites.

- **`simplifyJSON.py`**
  - **Purpose**: Simplifies packet data to essential information.
  - **Output**: Streamlined JSON file for easier analysis.
