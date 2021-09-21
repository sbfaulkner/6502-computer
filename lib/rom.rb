# frozen_string_literal: true

class Rom
  DEFAULT_SIZE = 32 * 1024

  def initialize(value, size: DEFAULT_SIZE)
    @bytes = Array.new(size, value)
  end

  def []=(addr, value)
    value = Array(value)
    @bytes[addr & 0x7fff, value.size] = value
    self
  end

  def write(path)
    File.write(path, @bytes.pack("C*"), mode: "wb")
  end
end
