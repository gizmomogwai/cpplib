def define_project(config)
  sources = FileList['**/*.cpp'].delete_if do |f|
    f.index('url/')
  end
  SourceLibrary.new(config, 'net').set_sources(sources)
end
