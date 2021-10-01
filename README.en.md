# QSynthesis

## Introduction

Singing composition tool, compatible with "singing composition for Halloween ー UTAU" all project files, sound source library, engine, and almost all plug-ins.

Use Qt development, including part of the independent cross-platform code, support Windows, MacOS and Linux systems.

Supports English, simplified Chinese, traditional Chinese, and Japanese.

Supports custom color themes, light and dark themes are provided by default.

## Deployment

### Windows

Download from the release page, unzip and move the entire folder to your personal directory, and manually create a desktop shortcut.

You are advised to grant administrator permissions.

### MacOS

Download from the release page, unzip and move the entire folder to your personal directory, use "Xattr -cr" to grant permissions to the directory, and then manually create your desktop avatar.

### Linux

Download from the release page, unzip and move the entire folder to your personal directory, use "chmod -r +x" to grant permissions to the folder, and then run "./QSynthesis -d "to automatically create. Desktop shortcut, cut to your desktop.

## Instructions

1. On Windows, this software is a 64-bit program, and some 32-bit engines and plug-ins may not be executed normally

2. Do not open the same voice folder in two processes. This may cause competition problems

## Dependencies

### Entropia File System Watcher

Cross-platform file system monitor, in the form of a static library linked to the executable file of this program.

Link: https://github.com/SpartanJ/efsw

+ Windows: The efSW static library (.lib) compiled with MSVC2019 and MinGW 8.1.0 has been prepared for this repository. If the compiler you used to compile this project is one of them, no changes should be made; if not, you may compile the library based on your compiler and modify the .pro file.

+ Linux64: This repository has prepared the efsw static library (.a) compiled by g++. For other distributions of Linux, you may compile this library yourself and modify the .pro file.

+ MacOS: This repository has prepared the EFSW static library (.a) compiled by Clang 64. If you are compiling this project by another compiler, you may compile the library yourself and modify the .pro file.

## Build from source code

### Qt 5.15.2

Install Qt 5.15.2 on your device and run qmake to compile directly.

### Run

In the working directory to create voice, plugins, config three directories, continue to create translations in the config, themes, two directories, can run normally.

### Launcher

Use additional launchers on Windows and Linux, only call platform API to set up working directory and create ontology process, the code is open source.

## Get engine

### Windows

There are many available engines, you can copy UTAU's own resampler.exe and wavtool.exe to QSynthesis directory and use them.

### MacOS & Linux

The release of macres (tn_fnds), which has been adapted across platforms, is available on the following page.

The release of world4utau, which has been adapted across platforms, is available on the following page.

The release of wavtool-yawu is available from the following page.

## Contribution

1.  Fork the repository
2.  Create Feat_xxx branch
3.  Commit your code
4.  Create Pull Request