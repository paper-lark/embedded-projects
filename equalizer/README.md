# Equalizer

**Prerequisites:**
- `avrdude`
- `avr-gcc`
- `ravedude`: `cargo +stable install ravedude`

Find serial port for board: `arduino-cli board list`
Run: `RAVEDUDE_PORT="/dev/cu.usbmodem21401" cargo run`


==================
Created with avr-hal template:
```bash
cargo generate --git https://github.com/Rahix/avr-hal-template.git
```
