cxx_configuration do
  static_lib("vecmath",
             sources: FileList['**/*.cpp'],
             includes: ['..'],
             dependencies: ["lang"]
            )
end
