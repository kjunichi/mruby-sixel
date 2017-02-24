# mruby-sixel   [![Build Status](https://travis-ci.org/kjunichi/mruby-sixel.svg?branch=master)](https://travis-ci.org/kjunichi/mruby-sixel)
SixelEncoder class

## install by mrbgems

- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'kjunichi/mruby-sixel'
end
```

## example

```ruby
encoder = SixelEncoder.new
encoder.encode_from_ppm ppmbuf
```

## License

under the MIT License:
- see LICENSE file
