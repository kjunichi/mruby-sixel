# mruby-sixel   [![Build Status](https://travis-ci.org/kjunichi/mruby-sixel.svg?branch=master)](https://travis-ci.org/kjunichi/mruby-sixel)
sixel for mruby class
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
p sixel for mruby.hi
#=> "hi!!"
t = sixel for mruby.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
