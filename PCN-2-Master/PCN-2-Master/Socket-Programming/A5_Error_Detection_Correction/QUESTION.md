# A5 — Error detection and correction using sockets

## Exam question
Implement checksum, CRC and Hamming code for error detection and correction.

## Important
Study the calculations separately:
- **Checksum:** calculate a one's-complement checksum and verify it at the receiver.
- **CRC:** perform modulo-2 division using a generator polynomial and check the remainder.
- **Hamming code:** add parity bits and correct a single-bit error under the standard assumptions.

The folders below contain separate sender/receiver demonstrations and separate READMEs:
- `Checksum/`
- `CRC/`
- `Hamming_Code/`

## Metrics
Validation/detection/correction success and optional processing or round-trip time. A checksum/CRC detects corruption; Hamming code can correct a single-bit error in the demonstrated code.
