cxx_configuration do
  static_lib("sgtools",
             sources: FileList["**/*.cpp"],
             includes: [".."],
             dependencies: ["sg"]
            )
end
