{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell.override {
  stdenv = pkgs.gcc10Stdenv;
} {
  buildInputs = [
    pkgs.bashInteractive
  ];
}
