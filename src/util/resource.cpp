#include "util/std.h" // Must be included first. Precompiled header with standard library includes.
#include "util/resource.h"
#include "util/util.h"
#include <limits.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

namespace NEAT {

    string find_resource(const string &name) {
#ifdef WIN32
		char home[MAX_PATH];
		// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule == NULL)
		{
			throw new exception("Own module handle not found.");
		}
		GetModuleFileName(hModule, home, (sizeof(home)));
#else
		char home[1024];
		ssize_t rc = readlink("/proc/self/exe", home, sizeof(home));
        if(rc < 1) {
            error("Couldn't resolve /proc/self/exe! Is this Linux?");
        }
        if(rc == sizeof(home)) {
            error("Possible buffer overrun.");
        }

        *strrchr(home, '/') = 0;
#endif

        return string(home) + "/res/" + name;
    }

}
