#!/usr/bin/env python3
"""Create the downloadable starter from the student-facing course directory."""
from pathlib import Path
import hashlib
import json
import re
import zipfile

ROOT = Path(__file__).resolve().parents[1]
KIT = "Advanced-Tutorial-1-Student-v1"
ARCHIVE = KIT + ".zip"
ROOT_FILES = {"README.md", "SOURCES.md", ".gitignore"}
ROOT_DIRS = {"notes", "projects", "hardware", "tools", "releases"}
HARDWARE_FILES = {"classwork-setup.md", "ioc-guide.md", "pin-mapping.md"}
LOCAL_DIRS = {"build", "CMakeFiles", "__pycache__", "__MACOSX"}
BUILD_SUFFIXES = {".elf", ".hex", ".bin", ".map", ".o", ".obj", ".pyc"}


def source_files():
    for path in ROOT.iterdir():
        if path.name == ".DS_Store":
            continue
        allowed = ROOT_DIRS if path.is_dir() else ROOT_FILES
        if path.name not in allowed:
            raise ValueError(f"Unexpected course entry: {path.name}")
    for path in (ROOT / "hardware").iterdir():
        if path.name not in HARDWARE_FILES:
            raise ValueError(f"Unexpected hardware entry: {path.name}")

    files = [ROOT / name for name in sorted(ROOT_FILES)]
    for directory in ("notes", "projects", "hardware", "tools"):
        for path in sorted((ROOT / directory).rglob("*")):
            if not path.is_file():
                continue
            relative = path.relative_to(ROOT)
            if LOCAL_DIRS.intersection(relative.parts) or path.name in {
                ".DS_Store", "CMakeCache.txt", "compile_commands.json"
            }:
                continue
            if path.is_symlink() or path.suffix.lower() in BUILD_SUFFIXES:
                raise ValueError(f"Unexpected package file: {relative}")
            files.append(path)
    return sorted(files)


def main():
    files = source_files()
    releases = ROOT / "releases"
    releases.mkdir(exist_ok=True)
    archive = releases / ARCHIVE
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as output:
        for path in files:
            relative = path.relative_to(ROOT)
            data = path.read_bytes()
            if relative.as_posix() == "README.md":
                text = data.decode("utf-8")
                # Avoid a download link to an archive inside that same archive.
                text = re.sub(
                    r"\[([^\]]+)\]\(releases/[^)]+\)",
                    r"\1 (provided as this archive)",
                    text,
                )
                data = text.encode("utf-8")
            info = zipfile.ZipInfo(
                str(Path(KIT) / relative), date_time=(2026, 10, 26, 0, 0, 0)
            )
            info.compress_type = zipfile.ZIP_DEFLATED
            info.create_system = 3
            info.external_attr = 0o100644 << 16
            output.writestr(info, data)
    with zipfile.ZipFile(archive) as output:
        if output.testzip() is not None:
            raise ValueError("Student archive CRC failed")
    entry = {
        "file": ARCHIVE,
        "files": len(files),
        "bytes": archive.stat().st_size,
        "sha256": hashlib.sha256(archive.read_bytes()).hexdigest(),
    }
    (releases / "archive-manifest.json").write_text(
        json.dumps([entry], indent=2) + "\n", encoding="utf-8"
    )
    print(json.dumps(entry, indent=2))


if __name__ == "__main__":
    main()
