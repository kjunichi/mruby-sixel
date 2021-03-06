MRuby::Gem::Specification.new('mruby-sixel') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Junichi Kajiwara'
  spec.cc.flags = `pkg-config libsixel --cflags`.chomp
  spec.linker.flags_before_libraries << `pkg-config libsixel --libs`.chomp
  spec.linker.flags << "-lsixel"
end
