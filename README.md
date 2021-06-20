# appupdater  
is a C++ cross-platform library to update desktop software.  

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

# Examples  
[updateExample](https://gitlab.com/desktopsoftwareupdater/updaterexamples)
