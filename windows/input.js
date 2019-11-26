const ffi = require('ffi-napi')
const StructType = require('ref-struct-napi')
const x64 = require('os').arch() === 'x64'

const INPUT_KEYBOARD = 1
const KEYEVENTF_KEYUP = 0x0002
const KEYEVENTF_SCANCODE = 0x0008

const Input = StructType({
  type: 'int',
  '???': 'int',
  wVK: 'short',
  wScan: 'short',
  dwFlags: 'int',
  time: 'int',
  dwExtraInfo: 'int64'
})

const User32 = ffi.Library('user32', {
  SendInput: ['int', ['int', Input, 'int']],
})

const convertKeyCodeToScanCode = (keyCode) => {
  let keys = '**1234567890-=**qwertyuiop[]**asdfghjkl;\'`*\\zxcvbnm,./'.split('')
  return keys.indexOf(String.fromCharCode(keyCode).toLowerCase())
}

const createInput = (keyCode, keyUp) => {
  const input = new Input()

  input.type = INPUT_KEYBOARD
  input.time = 0
  input.dwExtraInfo = 0
  input.wVK = 0
  input.dwFlags = keyUp ? KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP : KEYEVENTF_SCANCODE
  input.wScan = convertKeyCodeToScanCode(keyCode)

  return input
}

const keyUp = (keyCode) => {
  User32.SendInput(1, createInput(keyCode, true), x64 ? 40 : 28)
}

const keyDown = (keyCode) => {
  User32.SendInput(1, createInput(keyCode, false), x64 ? 40 : 28)
}

const keyTap = (keyCode) => {
  keyDown(keyCode)
  keyUp(keyCode)
}

module.exports = {
  keyUp,
  keyDown,
  keyTap
}