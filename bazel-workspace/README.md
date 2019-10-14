# This is a Bazel workspace.

## Build

`$` `bazel build //misc:hello `
```
Starting local Bazel server and connecting to it...
INFO: Writing tracer profile to '/usr/local/google/home/yuanyu/.cache/bazel/_bazel_yuanyu/951067d5c80e673c9c2b3b40f2e82e47/command.profile.gz'
INFO: Analyzed target //misc:hello (13 packages loaded, 52 targets configured).
INFO: Found 1 target...
Target //misc:hello up-to-date:
  bazel-bin/misc/hello
INFO: Elapsed time: 4.640s, Critical Path: 0.48s
INFO: 2 processes: 2 linux-sandbox.
INFO: Build completed successfully, 6 total actions

```

## Run

`bazel-workspace(master)$` `bazel-bin/misc/hello`
```
hello
```

## Ref

https://docs.bazel.build/versions/master/bazel-and-cpp.html
