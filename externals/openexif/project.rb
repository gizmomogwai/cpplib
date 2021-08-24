cxx_configuration do
  static_lib("openexif",
             sources: FileList["src/*.cpp"],
             includes: ["src", ],
             dependencies: []
            )
end
