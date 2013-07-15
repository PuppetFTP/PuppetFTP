#!/bin/sh

rm -f puppet.db.sqlite
cat db_structure.sql | sqlite3 puppet.db.sqlite
cat db_init.sql | sqlite3 puppet.db.sqlite
