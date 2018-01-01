cxx_configuration do
  flags = {
    :DEFINES => ['OSX']
  }

  static_lib("lang",
             :sources => FileList['**/*.cpp'].delete_if{ |f| f.index('WIN32') },
             :includes => ['..'],
             :toolchain => Provider.modify_cpp_compiler("gcc", flags))
end
