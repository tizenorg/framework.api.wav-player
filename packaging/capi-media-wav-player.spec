Name:       capi-media-wav-player
Summary:    A wav player library in Tizen C API
%if 0%{?tizen_profile_mobile}
Version: 0.1.0
Release:    16
%else
Version:    0.1.2
Release:    0
VCS:        framework/api/wav-player#capi-media-wav-player_0.1.0-10_1-3-g8d8a814371b4a4fd114ccfd8b8ed61b8655e699f
%endif
Group:      TO_BE/FILLED_IN
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(mm-sound)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-media-sound-manager)
Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A wav player library in Tizen C API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel



%prep
%setup -q


%build
%if 0%{?tizen_profile_mobile}
cd mobile
%else
cd wearable
%endif
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%if 0%{?tizen_profile_mobile}
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%else
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%endif

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%if 0%{?tizen_profile_mobile}
cd mobile
%else
cd wearable
%endif
mkdir -p %{buildroot}/usr/share/license
%if 0%{?tizen_profile_mobile}
cp LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}
%else
cp LICENSE %{buildroot}/usr/share/license/%{name}
%endif

%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%{_libdir}/libcapi-media-wav-player.so.*
%{_datadir}/license/%{name}
%if 0%{?tizen_profile_mobile}
%manifest mobile/capi-media-wav-player.manifest
%else
%manifest wearable/capi-media-wav-player.manifest
%endif

%files devel
%{_includedir}/media/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-media-wav-player.so
