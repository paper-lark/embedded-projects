#![no_std]
#![no_main]

use core::u8;
use arduino_hal::hal::Atmega;
use arduino_hal::hal::port::{PB0, PB1, PB2, PB3, PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7};
use arduino_hal::pac::USART0;
use arduino_hal::port::mode::Output;
use arduino_hal::port::Pin;
use panic_halt as _;
use embedded_hal::serial::Read;
use arduino_hal::prelude::*;
use arduino_hal::{DefaultClock};
use avr_hal_generic::port::mode::Input;
use avr_hal_generic::usart::Usart;

struct Pins {
    pub p2: Pin<Output, PD2>,
    pub p3: Pin<Output, PD3>,
    pub p4: Pin<Output, PD4>,
    pub p5: Pin<Output, PD5>,
    pub p6: Pin<Output, PD6>,
    pub p7: Pin<Output, PD7>,
    pub p8: Pin<Output, PB0>,
    pub p9: Pin<Output, PB1>,
    pub p10: Pin<Output, PB2>,
    pub p11: Pin<Output, PB3>,
}

impl Pins {
    fn len() -> usize {
        return 10;
    }
}

macro_rules! with_pin {
    ($pins:expr, $i:expr, $f:expr) => {
        {
            let i = $i;
            match i {
                0 => $f(&mut $pins.p2),
                1 => $f(&mut $pins.p3),
                2 => $f(&mut $pins.p4),
                3 => $f(&mut $pins.p5),
                4 => $f(&mut $pins.p6),
                5 => $f(&mut $pins.p7),
                6 => $f(&mut $pins.p8),
                7 => $f(&mut $pins.p9),
                8 => $f(&mut $pins.p10),
                9 => $f(&mut $pins.p11),
                _ => panic!("invalid pin: {}", i)
            };
        }
    };
}

fn read_number(serial: &mut Usart<Atmega, USART0, Pin<Input, PD0>, Pin<Output, PD1>, DefaultClock>) -> u8 {
    let mut input: u8 = 0;
    let mut had_input = false;
    loop {
        let b = nb::block!(serial.read()).void_unwrap() as char;
        if b >= '0' && b <= '9' {
            had_input = true;
            input = input * 10 + (b as u8 - '0' as u8);
        } else if had_input {
            return input;
        }
    }
}

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    let mut pins = Pins {
        p2: pins.d2.into_output(),
        p3: pins.d3.into_output(),
        p4: pins.d4.into_output(),
        p5: pins.d5.into_output(),
        p6: pins.d6.into_output(),
        p7: pins.d7.into_output(),
        p8: pins.d8.into_output(),
        p9: pins.d9.into_output(),
        p10: pins.d10.into_output(),
        p11: pins.d11.into_output()
    };

    loop {
        // read value
        let input = read_number(&mut serial);

        // light LEDs
        let scaled = input as usize * (Pins::len() + 1) / u8::MAX as usize;
        ufmt::uwriteln!(&mut serial, "Lighting up to {}\n", scaled).void_unwrap();
        for i in 0..Pins::len() {
            if i < scaled {
                with_pin!(pins, i, Pin::set_high);
            } else {
                with_pin!(pins, i, Pin::set_low);
            }
        }
    }
}
