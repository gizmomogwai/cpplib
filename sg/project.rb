cxx_configuration do
  static_lib("sg",
             sources: FileList["**/*.cpp"],
             includes: [".."],
             dependencies: ["lang", "util", "image", "vecmath"]
            )
end
