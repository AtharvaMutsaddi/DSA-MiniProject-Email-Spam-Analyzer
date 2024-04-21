### Overview:

This repository contains a C-based implementation of a spam email analyzer that utilizes data structures and algorithms to efficiently identify potential spam content in emails. The high-level design of the analyzer involves extracting keywords from spam emails using a spam-ham dataset sourced from Kaggle. These keywords, along with their TF-IDF (Term Frequency-Inverse Document Frequency) scores, are stored in a CSV file.

During program execution, the analyzer constructs a Trie data structure by reading the CSV file. Unlike traditional Trie implementations where the end of a word is marked, in this implementation, the TF-IDF score is mapped to each node in the Trie. This facilitates efficient searching and comparison of email contents against the stored keywords.

Additionally, the analyzer utilizes Bloom filters to probabilistically determine whether an input email ID is registered as spam. This enables quick identification of known spam email IDs.

### Key Components:

1. **Keyword Extraction and TF-IDF Calculation:**
   - Keywords are extracted from spam emails using a spam-ham dataset.
   - TF-IDF scores are calculated for each keyword.
   - Keywords and their corresponding TF-IDF scores are stored in a CSV file for later retrieval.

2. **Trie Construction:**
   - During program execution, a Trie data structure is constructed using the stored keywords and their TF-IDF scores.
   - Each node in the Trie is associated with the TF-IDF score of the corresponding keyword.

3. **Bloom Filters:**
   - Bloom filters are employed to efficiently determine whether an input email ID is registered as spam.
   - Registered spam email IDs are hashed and stored in the Bloom filter, allowing for quick probabilistic checks.

4. **Email Content Analysis:**
   - Email contents are analyzed by tokenizing the words.
   - The analyzer searches the Trie data structure for keywords present in the email content.
   - If significant matches are found, the email is flagged as potential spam.

### Technologies Used:

- C programming language for efficiency.
- CSV file handling for keyword storage.
- Trie data structure for efficient keyword searching.
- Bloom filters for probabilistic spam email identification.
