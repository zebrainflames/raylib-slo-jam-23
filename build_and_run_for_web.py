#!/usr/bin/env python3
from genericpath import exists
import os
import shutil
import sys

import http.server
import socketserver
import subprocess as subp
import signal

## USAGE: python3 build_and_run_for_web.py game
## where game is the name of the project sources folder, currently 'game' in this commit
## NOTE: this assumes that you have previously generated the emscripten build files as described in the readme, so
## in practice `cmake --build .` should already work in the emscripten build folder. After that this automation is useful

# Variables -- some depend on local setup
cmake_build = "cmake --build ."
emscripten_dir = "build-emscripten-debug"

if len(sys.argv) < 2:
    raise RuntimeError("Project name not specified!")

project = sys.argv[1]
print("Running emscripten build chain for project" + project)

print("Running build tasks...")
# Run through emscripten build task (needs to be set up according to README)
os.chdir(emscripten_dir)
try:
    subp.run(cmake_build, shell=True, check=True)
except subp.CalledProcessError as e:
    print("Emscripten Build failed!")
    sys.exit(1)

# copy files to output folder...
print("Copying files to build export dir...")
if not os.path.exists(project + "/dest"):
    os.mkdir(project + "/dest")
if os.path.exists(project + "/game.data"):
    shutil.copy(project + "/game.data", project + "/dest/game.data")
# the other files should always be there for a default raylib setup
shutil.copy(project + "/game.js", project+"/dest/game.js")
shutil.copy(project + "/game.html", project+"/dest/index.html")
shutil.copy(project + "/game.wasm", project+"/dest/game.wasm")
print("Files copied")



print("Starting web server at localhost:1234")
PORT = 1234
handler = http.server.SimpleHTTPRequestHandler
# change dir to builds before starting server for easy serving
os.chdir(project + "/dest")
#serve files from
with socketserver.TCPServer(("", PORT), handler) as httpd:
    print("Server started")
    httpd.serve_forever()

# define signal handler for graceful shutdowns
# TODO: doesn't work with IDE
def signal_handler(signal, frame):
    print( 'Exiting http server (Ctrl+C pressed)')
    try:
        if( httpd ):
            httpd.server_close()
    finally:
        sys.exit(0)

# Bind the required signals
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

# TODO: close neatly on interrupts