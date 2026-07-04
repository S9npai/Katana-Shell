{
  description = "Katana Shell: A minimal UNIX shell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

    in
    {
      packages = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          default = pkgs.stdenv.mkDerivation {
            pname = "katana-shell";
            version = "1.0.0";
            src = nixpkgs.lib.cleanSource ./.;
            #dontUnpack = true;

            nativeBuildInputs = with pkgs; [
              cmake
            ];

            buildInputs = with pkgs; [

            ];
          };
        }
      );

      devShells = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              cmake
              gcc
              gdb
            ];
          };
        }
      );
    };
}
