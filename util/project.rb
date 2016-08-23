cxx_configuration do 
  static_lib("util",
             sources: FileList['**/*.cpp'],
             includes: ['..'],
             dependencies: ['lang']
            )
end
