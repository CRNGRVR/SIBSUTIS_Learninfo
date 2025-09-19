#!/bin/bash
find $1 -mtime "+$2" -delete;
