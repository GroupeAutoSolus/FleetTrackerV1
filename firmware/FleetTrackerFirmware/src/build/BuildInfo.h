#pragma once

namespace BuildInfo {

const char* GetFirmwareVersion();
const char* GetGitCommit();
const char* GetBuildDate();
const char* GetBuildTime();
const char* GetBoardName();
const char* GetHardwareName();
const char* GetBuildType();

} // namespace BuildInfo
