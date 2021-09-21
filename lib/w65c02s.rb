# frozen_string_literal: true

module W65C02S
  extend self

  def word(value)
    [value & 0x00ff, (value & 0xff00) >> 8]
  end

  def lda(operand)
    [0xA9, operand]
  end

  def nop
    [0xEA]
  end

  def sta(address)
    [0x8D] + word(address)
  end
end
