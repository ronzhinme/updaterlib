# appupdater  
is a C++ cross-platform framework to update desktop software.  

# How it works
1. Framework checks the URL you specified for info about versions and download it. 
   This URL is called InfoUrl in the framework.
   Info about versions is presented as a simple XML file
1. Framework parse versions info XML file and try to find the next version for the application.
1. If there is a new version of the application is available in the version info XML file then the framework will download the data from the URL specified in XML for that version.
1. After the downloading is completed then the framework will check the SHA-512 signature of data.
1. Framework will make execute installer operation for Windows with specified arguments in XML.
1. Framework will make execute installer operation for Linux with specified arguments in XML.
1. Framework will make install DMG operation for macOS.

# Version Info file structure
```
<updateInfo>
<channel type="alpha">
<version id="0.0.0.1" unixtime="0" size="1023" active="true" critical="false" url="" notes="First version" signature=""></version>
<version id="0.0.1.1" unixtime="1095292800" size="1023" active="false" critical="true" url="" notes="" signature=""></version>
<version id="0.0.1.1" unixtime="1095292801" size="1023" active="true" critical="false" url="" notes="Active critical version \nInstall It \nAny String" signature=""></version>
<version 
         id="0.1.1.1"          // id        - [required] main info about version     
         unixtime="1095292802" // unixtime  - [optional] helps to decide which version newer if ids equals
         size="29696808"       // size      - [optional] helps to show correct downloading progress
         active="true"         // active    - [required] enabled/disabled version to update
         critical="false"      // critical  - [required] if critical is true then this version will downloaded even there is newer version exists
         url="https://..."     // url       - [required] url where the installer is placed
         notes=""              // notes     - [optional] just notes. Not used in framework yet
         signature="...."      // signature - [required] SHA-512 hash of installer
         updateargs=""         // updateargs- [optional] extra options when installer started
        ></version>
</channel>
<channel type="beta"></channel>
<channel type="test"></channel>
</updateInfo>
```
[XML example](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/blob/master/appUpdateSample_Win.xml)

It supports: 
- `Windows`  
- `macOS`  
- `Linux`   

It built with some other open source libraries:  
* [Curl](https://github.com/curl/curl)
* [pugixml](https://github.com/zeux/pugixml)
* [OpenSSL](https://github.com/openssl/openssl)

# Prerequisites  
### Linux  
https://gitlab.com/desktopsoftwareupdater/updaterlib/-/blob/master/.gitlab-ci.yml#L11
```
apt-get install -y git cmake build-essential autoconf libtool pkg-config libssl-dev
```
### Windows  
### macOS  
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
[QML example](https://gitlab.com/desktopsoftwareupdater/updaterexamples/-/tree/master/qml_example)  
