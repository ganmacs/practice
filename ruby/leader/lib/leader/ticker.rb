module Leader
  class Ticker
    def initialize(duration, &block)
      @duration = duration
      @block = block
    end

    def start
      current = Thread.current
      @t ||= Thread.new do
        loop do
          begin
            @block.call
          rescue => e
            current.raise(e)
          end
          sleep(@duration)
        end
      end
    end

    def stop
      @t.kill
    end
  end
end
