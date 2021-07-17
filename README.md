# appupdater  
is a C++ cross-platform framework to update desktop software.  

It supports: 
- `Windows`  
- `macOS`  
- `Linux`   

It built with some other open source libraries:  
* [Curl](https://github.com/curl/curl)
* [pugixml](https://github.com/zeux/pugixml)
* [OpenSSL](https://github.com/openssl/openssl)

# Prerequisites  
Linux  
https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L11
```
apt-get install -y git cmake build-essential autoconf libtool pkg-config libssl-dev
```
Windows  
macOS  
1. install Xcode with git. Just try `git` it will install Xcode with git if need.
1. install brew `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
1. `brew install autoconf automake libtool openssl cmake`

# Build
1. build the `curl` library  
[Linux](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L17)  
[Windows](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L60)  
[macOS](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L102)  

1. build the `appupdater` library  
[Linux](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L25)  
[Windows](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L67)  
[macOS](https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L110)  

# Using
1. use header 
```
#include <updaterInterface.h>
```

1. link library 
```
appUpdaterShared
```

1. get the updater instance 
```
auto updater = getUpdaterInstance();
```

1. set the current version info 
```
//current version
std::string version("0.0.0.1");
setCurrentVersion(updater, version.c_str(), version.length());

//url where the fileInfo is placed
const std::string infoUrl("https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/raw/master/appUpdateSample_Win.xml");
setInfoUrl(updater, infoUrl.c_str(), infoUrl.length());

//channel ("alpha", "beta", "rc", "stable", or any other string to identify particular version)
setChannel(updater, "alpha", 5);
```

1. check and update for a new version in one command
```
checkAndUpdate(updater);
```

You may find more details in other examples.

# Examples  
[updateExample all projects](https://gitlab.com/desktopsoftwareupdater/updaterexamples)  
[example with separate commands](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/blob/master/main.cpp)  
[example with all-in-one commnad](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/blob/master/allInOne.cpp)  
[example with downloading pause](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/blob/master/pause_resume.cpp)  
[QML exmple](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/tree/master/qml_example)  
