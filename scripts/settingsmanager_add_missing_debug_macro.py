#!/usr/bin/env python


Import("env")

import os

settingsmanager_location = '{}/.pio/libdeps/nodemcuv2/Settings Manager_ID5950/src'.format(env['PROJECT_DIR'])
if os.path.exists(settingsmanager_location):
    debug_macro_content = '''#define DEBUGER
#ifdef DEBUGER
#define DEBUG_BEGIN Serial.begin(115200)
#else
#define DEBUG_BEGIN 
#endif   
#ifdef DEBUG_SETTINGS
#  define DBG(x)    \\
    this->debug->print(x); \\
    this->debug->flush();
#  define DBGLN(x, ...)                             \\
    this->debug->printf("[%s](%d): ", __FILE__, __LINE__); \\
    this->debug->printf(x, ##__VA_ARGS__);                 \\
    this->debug->println("");                              \\
    this->debug->flush();
#else
#  define DBG(X)
#  define DBGLN(X, ...)
#endif // DEBUG_SETTINGS    '''
    if os.path.exists('{}/debug_macro.h'.format(settingsmanager_location)):
        os.unlink('{}/debug_macro.h'.format(settingsmanager_location))
    debug_macro_file = open('{}/debug_macro.h'.format(settingsmanager_location), 'w+')
    debug_macro_file.write(debug_macro_content)
    debug_macro_file.close()
