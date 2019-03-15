#!/usr/bin/env bash

read -r -d '' config_modification_notification <<EOF
The entry 'include.path' is not configured on your machine.

We need to modify your git configuration to include the configuration
provided by this repository.

Continue?
EOF

# Set the prompt, which is stored in PS3:
PS3="Enter the number corresponding to your choice: "

currentPath=`git config include.path`
if [[ $? -ne 0 || ! $currentPath =~ "../.gitconfig" ]]; then
    echo "$config_modification_notification"
    select yn in "Yes" "No"; do
        case $yn in
            # Only confirm on explicit answer; everything else aborts the process.
            Yes ) break;;
            *   ) echo "Aborted."; exit;;
        esac
    done
    reply=`git config include.path "../.gitconfig"`
    if [[ $? -eq 0 ]]; then
        echo "Configuration updated!"
    else
        echo "Failed to update configuration: response = '$reply'."
    fi
else
    echo "No modification is necessary."
fi
