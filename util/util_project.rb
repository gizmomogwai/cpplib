def define_project(config)
  sources = FileList['**/*.cpp']
  SourceLibrary.new(config, 'util').set_sources(sources)
end
