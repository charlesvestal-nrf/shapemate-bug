# ShapeMate Firmware — Memfault MCP Demo

This repo contains fake firmware for the "ShapeMate" fitness tracker. It has three real bugs that produce real issues in Memfault. This guide walks through demoing how Claude Code can use the Memfault MCP server to investigate crashes and fix them directly in the codebase.

## Prerequisites

- [Claude Code](https://docs.anthropic.com/en/docs/claude-code) installed (`npm install -g @anthropic-ai/claude-code`)
- A GitHub account with push access
- Access to the ShapeMate Memfault project

## Setup

### 1. Fork and clone the repo

Fork this repo on GitHub, then clone your fork:

```bash
git clone https://github.com/charlesvestal-nrf/shapemate-bug.git
cd shapemate-bug
```

### 2. Configure the Memfault MCP server

Create `.claude/settings.json` in the repo root:

```bash
mkdir -p .claude
cat > .claude/settings.json << 'EOF'
{
  "mcpServers": {
    "memfault": {
      "type": "sse",
      "url": "https://mcp.memfault.com/sse",
      "headers": {
        "Authorization": "Basic <YOUR_MEMFAULT_API_KEY>"
      }
    }
  }
}
EOF
```

Replace `<YOUR_MEMFAULT_API_KEY>` with a Basic Auth User API Key. You can find this by logging into Demo with the francois account in 1password under the profile. Enable developer mode (command+shift+d) to show "Copy as Basic Auth Token" 

### 3. Look up the current issue IDs

Issue IDs may change between Memfault environments. Find the issues for `gatt_send_next_pkt`, `send_fitness_data_to_companion` and `check_shortcut` and copy their IDs from the URL. For instance

## The Demo

### Flow 1: Investigate and fix a single issue

Start Claude Code in the repo:

```bash
claude
```

**Prompt:**

> "Memfault issue <ISSUE_ID> is causing crashes on our ShapeMate devices. Can you investigate the root cause and open a PR with a fix?"

**What happens:** Claude will:
1. Call the Memfault MCP to fetch the issue details and trace data
2. Read the stacktrace and logs from the crash
3. Find the corresponding source files in the repo
4. Identify the bug and write a fix
5. Create a branch and open a PR on GitHub

### Flow 2: Triage multiple issues at once

**Prompt:**

> "We have three open Memfault issues: <ID_1>, <ID_2>, and <ID_3>. Can you investigate all of them, tell me which is the most critical, and fix the highest-priority one first?"

**What happens:** Claude will:
1. Fetch all three issues in parallel via the MCP
2. Compare severity (device count, trace count, fault type)
3. Rank them and explain the reasoning
4. Fix the most critical one and open a PR

### Flow 3: Open-ended investigation

**Prompt:**

> "Our ShapeMate devices have been experiencing increased crash rates. Can you look at the open Memfault issues and figure out what's going on?"

**What happens:** Claude will:
1. Query Memfault for open issues
2. Pull traces and analyze crash patterns
3. Identify that all three bugs were introduced in firmware v1.1.0
4. Provide a summary of root causes and recommended fixes

## Talking Points

- **No context-switching**: The developer never leaves their terminal. Crash data from Memfault flows directly into the coding workflow.
- **Real crash data, real fixes**: Claude isn't guessing — it reads actual stacktraces, register dumps, and device logs from production devices to pinpoint bugs.
- **Parallel investigation**: Multiple issues can be triaged simultaneously, something that would take a human engineer much longer to context-switch between.
- **End-to-end**: From "we have a crash" to "here's a PR with the fix" in a single conversation.

## Resetting the Demo

To reset the repo back to the buggy state after PRs have been merged:

```bash
git checkout main
git reset --hard origin/main
git push --force
```

Or simply re-fork from the upstream repo.
