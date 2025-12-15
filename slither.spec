%define gh_user giosali

Name:           slither
Version:        1.0.0
Release:        1%{?dist}
Summary:        An application for Linux that allows you to simulate keyboard shortcuts with touchpad gestures

License:        MIT
URL:            https://github.com/%{gh_user}/%{name}
Source0:        %{url}/archive/v%{version}.tar.gz

BuildRequires:  gcc-c++ cmake make libinput-devel libudev-devel libevdev-devel spdlog-devel wxGTK3 wxGTK-devel

%description
Slither is a touchpad utility application designed for Linux (GNOME on Wayland). With Slither, you can streamline your workflow by transforming touchpad gestures into keyboard combinations to boost your productivity.

%prep
%autosetup


%build
%cmake
%cmake_build


%install
%cmake_install

%post
desktop-file-install --dir=/usr/share/applications %{name}.desktop
xdg-icon-resource install --novendor %{name}.png

%postun
rm /usr/share/applications/%{name}.desktop
xdg-icon-resource uninstall %{name}

%files
%license LICENSE
%doc README.md
%{_bindir}/%{name}


%changelog
* Fri Nov 01 2024 giosali <gio_sali@outlook.com> - 1.0.0
- Initial release.