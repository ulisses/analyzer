module Paths_language_c (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName
  ) where

import Data.Version (Version(..))
import System.Environment (getEnv)

version :: Version
version = Version {versionBranch = [0,3,2,1], versionTags = []}

bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/usr/local/bin"
libdir     = "/usr/local/lib/language-c-0.3.2.1/ghc-7.0.2"
datadir    = "/usr/local/share/language-c-0.3.2.1"
libexecdir = "/usr/local/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catch (getEnv "language_c_bindir") (\_ -> return bindir)
getLibDir = catch (getEnv "language_c_libdir") (\_ -> return libdir)
getDataDir = catch (getEnv "language_c_datadir") (\_ -> return datadir)
getLibexecDir = catch (getEnv "language_c_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
