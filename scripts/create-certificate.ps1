# Check if running as Administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

if (-not $isAdmin) {
    Write-Warning "Not running as Administrator. Certificate will be created but may not be fully trusted."
}

# Check if certificate already exists
$cert = Get-ChildItem -Path Cert:\CurrentUser\My | Where-Object { $_.Subject -eq "CN=Kyle Buchanan" }

if ($cert) {
    Write-Host "Certificate already exists: $($cert.Thumbprint)"
} else {
    # Create self-signed certificate
    $cert = New-SelfSignedCertificate `
        -Type CodeSigningCert `
        -Subject "CN=Kyle Buchanan" `
        -CertStoreLocation "Cert:\CurrentUser\My" `
        -NotAfter (Get-Date).AddYears(5)
    
    Write-Host "Certificate created: $($cert.Thumbprint)"
    
    # Export and import to Trusted Root (requires admin)
    if ($isAdmin) {
        $tempCert = [System.IO.Path]::GetTempFileName() + ".cer"
        Export-Certificate -Cert $cert -FilePath $tempCert
        Import-Certificate -FilePath $tempCert -CertStoreLocation Cert:\LocalMachine\Root
        Remove-Item $tempCert
        Write-Host "Certificate added to Trusted Root"
    } else {
        Write-Warning "Run PowerShell as Administrator to add certificate to Trusted Root"
        Write-Host "Manual step: Run this script as Administrator, or run:"
        Write-Host "  `$cert = Get-ChildItem Cert:\CurrentUser\My | Where Subject -eq 'CN=Kyle Buchanan'"
        Write-Host "  Export-Certificate -Cert `$cert -FilePath cert.cer"
        Write-Host "  Import-Certificate -FilePath cert.cer -CertStoreLocation Cert:\LocalMachine\Root"
    }
}