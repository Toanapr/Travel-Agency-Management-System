#!/bin/bash
# filepath: f:/TravelAgency/change_commit_date.sh

NEW_DATE="2025-05-17T22:55:24"

# Amend the most recent commit with the new date
export GIT_COMMITTER_DATE="$NEW_DATE"
export GIT_AUTHOR_DATE="$NEW_DATE"
git commit --amend --no-edit --date="$NEW_DATE"

echo "Commit date has been changed to: $NEW_DATE"