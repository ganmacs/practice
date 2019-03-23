use msg::packer;

#[test]
fn write_bool() {
    let mut buf = vec![];
    packer::write_bool(true, &mut buf).unwrap();
    packer::write_bool(false, &mut buf).unwrap();
    assert_eq!(buf, &[0xc3, 0xc2]);
}

// #[test]
// fn decode_from_signed_int() {
//     let mut buf = vec![];
//     (-1 as i64).encode_to(&mut buf);
//     (-1 as i32).encode_to(&mut buf);
//     (-1 as i16).encode_to(&mut buf);
//     (-1 as i8).encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[
//             0xd3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0xff, 0xff, 0xff, 0xff,
//             0xd1, 0xff, 0xff, 0xd0, 0xff
//         ]
//     );
// }

// #[test]
// fn decode_from_unsigned_int() {
//     let mut buf = vec![];
//     (1 as u64).encode_to(&mut buf);
//     (1 as u32).encode_to(&mut buf);
//     (1 as u16).encode_to(&mut buf);
//     (1 as u8).encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[
//             0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xce, 0x00, 0x00, 0x00, 0x01,
//             0xcd, 0x00, 0x01, 0xcc, 0x01
//         ]
//     );
// }

// #[test]
// fn decode_from_str() {
//     let mut buf = vec![];
//     "le message".encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[0xaa, 0x6c, 0x65, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65]
//     );
// }

// #[test]
// fn decode_from_bin() {
//     let mut buf = vec![];
//     let msg1: &[u8] = "le message".as_bytes();
//     msg1.encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[0xc4, 0x6c, 0x65, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65]
//     );
// }

// #[test]
// fn decode_from_fixarray() {
//     let mut buf = vec![];
//     vec![9 as i32, 42, -9].encode_to(&mut buf);
//     assert_eq!(buf, &[0x93, 0x00, 0x2a, 0xf7]);
// }
