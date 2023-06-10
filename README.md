# Ava - Assitant Virtual Answer for CLI

Ava is tool designed to provide a faster and more efficient way to search information by parsing HTML from Google search results in the command line interface (CLI). It aims to enchence the search experience and assist users in finding relevant information quickly

**Note: Ava is currently under development and still requires improvements.**

## Installation
To install ava, follow these steps:
1. Clone the repository
```bash
git clone https://github.com/0xFA99/Ava.git
```
2. Navigate to the project directory
```bash
cd Ava
```
3. Installation
```bash
make install
```

## Usage
```bash
Usage: ava [options] "query"
```

Replace `"query"` with your desired search query. Ava will then parse the Google search search results and display relevant information in the command line.

## Example
Here's an example of how to use ava:
```bash
$ ava "how to exit vim"
-----
Remember Esc : As mentioned above, pressing Esc is a key step in exiting Vim. If you are having trouble exiting insert mode or entering commands, try pressing Esc first to return to normal mode.
-----
```
This command will search for the query "how to exit vim" on Google and display relevant information parsed from the search result

## Contributing
Contributions to ava are welcome! If you have any suggestions, bug reports, or features requests, please open an issue on the <a href="https://github.com/0xFA99/Ava/issues">GitHub repository</a>

## ACKNOWLEDGEMENTS
- <a href="https://github.com/curl/curl">curl</a> - command-line tool for transferring data specified with URL syntax.
- <a href="https://gitlab.gnome.org/GNOME/libxml2">libcurl</a> - XML parser and toolkit.
- <a href="https://github.com/Bugswriter/tuxi">tuxi</a> - inspiration.
---
Feel free to customize this template to suit your project's specific needs. Make sure to include relevant sections such as project description, features, installation instructions, usage example, contribution guidelines, and license information.
