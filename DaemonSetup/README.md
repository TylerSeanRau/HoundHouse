# HoundHouse Daemon Setup

This file explains how to use the files in this directory to get the HoundHouse service running as a systemd service.

## Daemon Install

1.  Be sure a copy of the `HoundHouse` executable is in `/usr/bin/`

2.  Move `spi.rules` into its desired location

        mv spi.rules /etc/udev/rules.d/.

3.  Move `houndhouse.service` into its desired location

        mv houndhouse.service /etc/systemd/user/.

4.  Enable the service

        systemctl enable /etc/systemd/user/houndhouse.service

## Cleaning up some issues that cause slow boot times

There are a couple of issues that cause unnessary slow boot times on a raspberry pi running ubuntu, here's how to fix those.

- The systemd-networkd-wait-online.service is ment to wait until the device is connected to the network succesffuly, however by default it waits for a specific interface to connect. Given this after 2 minutes of waiting for the specified device to connect to the network this service times out and failes.

  - My fix for this is to add the `--any` flag to the `ExecStart` line in `/lib/systemd/system/systemd-networkd-wait-online.service`

    - This allows systemd-networkd-wait-online.service to complete once **any** device is connected

- For some reason, by default in ubuntu, the ib*user module is attempted to be loaded by /lib/modules-load.d/open-iscsi.conf during systemd-modules-load.service; however the packages needed for ib_user are not included by default. \_w.t.f.*

  - To fix this, open `/lib/modules-load.d/open-iscsi.conf` and comment out the line for `ib_user` with a `#` at the beginning of the line.
