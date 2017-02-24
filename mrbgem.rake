MRuby::Gem::Specification.new('mruby-sixel') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Junichi Kajiwara'
  spec.linker.flags << "-lsixel"
end
