
from pathlib import Path
from html import escape
from urllib.parse import quote

folder = Path(__file__).parent.parent
files = sorted(folder.glob("*.c"), key=lambda f: f.name.lower())

links = ""

for file in files:
    name = escape(file.name)
    url = "../" + quote(file.name, safe="")
    links += f'            <a href="{url}">{name}</a>\n'

html = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>C Programs</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <main>
        <h1>C Programs<span>.</span></h1>
        <p class="subtitle">A collection of my C projects</p>

        <div class="file-list">
{links}        </div>

        <footer>{len(files)} programs · Written in C</footer>
    </main>
</body>
</html>
"""

(Path(__file__).parent / "index.html").write_text(html, encoding="utf-8")

print(f"Homepage updated! Found {len(files)} C programs.")
