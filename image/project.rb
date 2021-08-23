cxx_configuration do
  static_lib("image",
             sources: FileList["**/*.cpp"],
             includes: [".."],
             dependencies: ["lang", "io", "openexif", BinaryLibrary.new("jpeg"), BinaryLibrary.new("png")]
            )
end
