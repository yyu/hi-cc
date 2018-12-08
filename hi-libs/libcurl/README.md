## libcurl

### on macos

    $ brew install curl
    Updating Homebrew...
    Ignoring path homebrew-cask/
    ==> Auto-updated Homebrew!
    Updated Homebrew from 77e6a9275 to 38493a35a.
    Updated 2 taps (homebrew/cask and homebrew/core).
    ==> New Formulae
    php@7.2
    ==> Updated Formulae
    imagemagick ✔                qt ✔                         aubio           gcc@7           kubernetes-helm     nwchem              pgweb       postgis         shellcheck      xml-security-c
    nettle ✔                     rust ✔                       citus           gnuradio        libpqxx             opencv@2            php         postgresql      shibboleth-sp   xml-tooling-c
    numpy ✔                      ansible                      dbus            graph-tool      logstash            pandoc-crossref     php@5.6     pyenv           stunnel
    openblas ✔                   arcade-learning-environment  elasticsearch   kibana          mutt                pgroonga            php@7.1     ruby-build      temporal_tables
    opencv ✔                     astrometry-net               fx              knot-resolver   nss                 pgrouting           phpunit     scipy           urh
    ==> Deleted Formulae
    php@7.0                      pldebugger

    ==> Downloading https://homebrew.bintray.com/bottles/curl-7.62.0.sierra.bottle.1.tar.gz
    ######################################################################## 100.0%
    ==> Pouring curl-7.62.0.sierra.bottle.1.tar.gz
    ==> Caveats
    curl is keg-only, which means it was not symlinked into /usr/local,
    because macOS already provides this software and installing another version in
    parallel can cause all kinds of trouble.

    If you need to have curl first in your PATH run:
      echo 'export PATH="/usr/local/opt/curl/bin:$PATH"' >> ~/.bash_profile

    For compilers to find curl you may need to set:
      export LDFLAGS="-L/usr/local/opt/curl/lib"
      export CPPFLAGS="-I/usr/local/opt/curl/include"

    For pkg-config to find curl you may need to set:
      export PKG_CONFIG_PATH="/usr/local/opt/curl/lib/pkgconfig"


    zsh completions have been installed to:
      /usr/local/opt/curl/share/zsh/site-functions
    ==> Summary
    🍺  /usr/local/Cellar/curl/7.62.0: 445 files, 3.2MB

    $ PKG_CONFIG_PATH="/usr/local/opt/curl/lib/pkgconfig" pkg-config --libs libcurl                                                                                                                                              
    -L/usr/local/Cellar/curl/7.62.0/lib -lcurl

    $ PKG_CONFIG_PATH="/usr/local/opt/curl/lib/pkgconfig" pkg-config --cflags libcurl                                                                                                                                            
    -I/usr/local/Cellar/curl/7.62.0/include
