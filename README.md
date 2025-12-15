# Slither

An application for Linux that allows you to simulate keyboard shortcuts with touchpad gestures.

## Introduction

Slither is a touchpad utility application designed for Linux (GNOME on Wayland). With Slither, you can streamline your workflow by transforming touchpad gestures into keyboard combinations to boost your productivity. The following touchpad gestures are currently supported:

- Swipe gestures
- Pinch gestures
- Hold gesture

## Installation

### Fedora

```
sudo dnf copr enable giosali/slither
sudo dnf install slither
systemctl --user enable --now slither.service
```
