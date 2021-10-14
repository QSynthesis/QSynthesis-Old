#include "BaseDirInfo.h"
#include "QUtils.h"

BaseDirInfo::BaseDirInfo() : BaseFile(Qs::Default) {
}

BaseDirInfo::~BaseDirInfo() {
}

BaseDirInfo::BaseDirInfo(Qs::VariableSource source) : BaseFile(source) {
}

QString BaseDirInfo::filename() const {
    return m_filename + Slash + infoFilename();
}

QString BaseDirInfo::dirname() const {
    return BaseFile::filename();
}

void BaseDirInfo::setDirname(const QString &dirname) {
    BaseFile::setFilename(dirname);
}

QString BaseDirInfo::infoFilename() const {
    return "";
}
