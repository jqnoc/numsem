
# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.3.0 (2018.10.15)
### Added
- AMPL/Gurobi option for calculation Frobenius number based on Greenberg's algorithm (much faster than default algorithm).
- Apéry set calculation (requires AMPL and Gurobi).
- Command options for all features (see full list with --help).
- Generators of numerical semigroup now taken from file.

### Changed
- Old console options are no longer supported, use new command options.

### Removed
- Deleted /ampl directory. AMPL files are now generated when needed.

## 0.2.0 (2018.07.25)
### Added
- Calculation for the Sylvester denumerant.
- Calculation of the Sylvester denumerant up to a certain bound.

## 0.1.0 (2018.05.30)
### Added
- Preliminary version with files from older project.
- Frobenius number (slow algorithm).
- Set of gaps (slow algorithm).
- Membership problem (slow algorithm).
