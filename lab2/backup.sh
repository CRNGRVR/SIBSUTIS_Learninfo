#!/bin/bash
d=$(date +%d-%m-%Y_%H-%M-%S);
tar -czf "backup_at_$d.tar.gz" $1
find -name "[backup_at]*[.tar.gz]" -type f -mtime +7 -delete
