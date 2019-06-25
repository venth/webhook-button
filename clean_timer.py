#!/usr/bin/env python


Import("env")

import os, shutil

etl_timer_location = '{}/.piolibdeps/Embedded Template Library/src/c'.format(env['PROJECT_DIR'])
if os.path.exists(etl_timer_location):
    shutil.rmtree(etl_timer_location)
