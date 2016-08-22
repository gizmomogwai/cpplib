cxx_configuration do
  flags = {
    :DEFINES => ['OSX']
  }

  source_lib("lang",
             :sources => FileList['**/*.cpp'].delete_if{|f|f.index('WIN32')},
             :includes => ['..'],
             :toolchain => Provider.modify_cpp_compiler("GCC", flags))
end
