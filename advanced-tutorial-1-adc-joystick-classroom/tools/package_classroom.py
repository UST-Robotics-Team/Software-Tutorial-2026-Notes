#!/usr/bin/env python3
"""Package the independent classroom starter; exclude local build/IDE caches."""
from pathlib import Path
import hashlib
import json
import re
import zipfile

ROOT = Path(__file__).resolve().parents[1]
NAME = "ADC-Joystick-Classroom-v2"
SKIP_DIRS = {"build", ".git", ".settings", ".vscode", "MXTmpFiles", "__pycache__", "releases"}
SKIP_FILES = {".DS_Store", ".mxproject", "CMakeCache.txt", "compile_commands.json"}
BUILD_SUFFIXES = {".elf", ".hex", ".bin", ".map", ".o", ".obj", ".pyc", ".log"}


def main():
    output_dir = ROOT / "releases"
    output_dir.mkdir(exist_ok=True)
    archive = output_dir / (NAME + ".zip")
    files = []
    for path in sorted(ROOT.rglob("*")):
        if not path.is_file():
            continue
        relative = path.relative_to(ROOT)
        if SKIP_DIRS.intersection(relative.parts) or path.name in SKIP_FILES:
            continue
        if path.name.endswith("_save") or path.suffix.lower() in BUILD_SUFFIXES:
            continue
        if path.is_symlink() or "instructor" in relative.parts or "solutions" in relative.parts:
            raise ValueError(f"Unexpected classroom package file: {relative}")
        files.append(path)
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as target:
        for path in files:
            relative = path.relative_to(ROOT)
            info = zipfile.ZipInfo((Path(NAME) / relative).as_posix(), (2026, 10, 27, 0, 0, 0))
            info.compress_type = zipfile.ZIP_DEFLATED
            info.create_system = 3
            info.external_attr = 0o100644 << 16
            data = path.read_bytes()
            if relative.as_posix() == "README.md":
                data = re.sub(r"\[([^\]]+)\]\(releases/[^)]+\)",
                              r"\1 (provided as this archive)", data.decode()).encode()
            target.writestr(info, data)
    with zipfile.ZipFile(archive) as target:
        if target.testzip() is not None:
            raise ValueError("Classroom archive CRC failed")
    manifest = {"file": archive.name, "files": len(files), "bytes": archive.stat().st_size,
                "sha256": hashlib.sha256(archive.read_bytes()).hexdigest()}
    (output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(json.dumps(manifest, indent=2))


if __name__ == "__main__":
    main()
