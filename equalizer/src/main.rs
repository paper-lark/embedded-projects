#![no_std]
#![no_main]

use arduino_hal::hal::port::{PB0, PB1, PB2, PB3, PD2, PD3, PD4, PD5, PD6, PD7};
use arduino_hal::port::mode::Output;
use arduino_hal::port::Pin;
use panic_halt as _;
use arduino_hal::prelude::*;

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

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

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

    let mut i: u8 = 0;
    let mut cnt: u8 = 0;
    loop {
        if cnt % 2 == 0 {
            with_pin!(pins, i, Pin::set_high);
        } else {
            with_pin!(pins, i, Pin::set_low);
        }
        arduino_hal::delay_ms(500);
        i = i + 1;
        if i > 9 {
            i = 0;
            cnt += 1;
        }
    }
}
